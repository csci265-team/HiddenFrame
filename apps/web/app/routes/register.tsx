/* eslint-disable @typescript-eslint/no-explicit-any */
import type { MetaFunction } from "@remix-run/node";
import { PageHeader, Button, Input } from "../components";
import { BASE_API_URL } from "../lib/consts";
import { useState } from "react";
import { useSearchParams } from "@remix-run/react";
import { hashPassword } from "../lib/utils";
import { toast } from "sonner";
// import { useLoaderData } from "@remix-run/react";

export const meta: MetaFunction = () => {
    return [
        { title: "HiddenFrame" },
        { name: "description", content: "Welcome to HiddenFrame!" },
    ];
};

export default function Register() {

    const [loading, setLoading] = useState(false);
    const [searchParams] = useSearchParams();
    const inviteId = searchParams.get("inviteId");

    const register = async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
        setLoading(true);

        const username = e.currentTarget.username.value;

        const hashedPassword = await hashPassword(e.currentTarget.password.value);

        const resp = await fetch(`${BASE_API_URL}/register`, {
            method: "POST",
            body: JSON.stringify({
                inviteId,
                username,
                password: hashedPassword,
            }),
            headers: {
                contentType: "application/json",
            }
        });

        if (resp.ok) {
            toast.success("Registered successfully");
            window.location.href = "/login";
        } else {
            const error = await resp.text();
            toast.error("Unable to register", { description: error });
            setLoading(false)
        }
    }

    return (
        <div className="flex items-center justify-center h-full">
            <div className="flex flex-col items-center gap-8 h-full">
                <PageHeader />

                <h2 className="text-2xl font-black ">Register</h2>

                <div className="flex flex-col gap-4 p-4">
                    <form className="flex flex-col gap-4 p-4" onSubmit={register}>
                        <Input type="text" id="username" name="username" placeholder="Username" />
                        <Input type="password" id="password" name="password" placeholder="Password" />
                        <Button loading={loading} type="submit">Register</Button>
                    </form>
                </div>
            </div>
        </div>
    );
}
