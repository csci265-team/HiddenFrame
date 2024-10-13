import type { MetaFunction } from "@remix-run/node";

export const meta: MetaFunction = () => {
  return [
    { title: "HiddenFrame" },
    { name: "description", content: "Welcome to Remix!" },
  ];
};

export default function Index() {
  return (
    <div className="flex h-screen items-center justify-center  bg-colors-hf-beige dark:bg-colors-hf-brown">
      <div className="flex flex-col items-center gap-16">
        <header className="flex flex-col items-center gap-9">
          <h1 className="text-4xl font-[Outfit] font-black text-colors-hf-brown dark:text-colors-hf-beige">HiddenFrame</h1>
        </header>
      </div>
    </div>
  );
}

